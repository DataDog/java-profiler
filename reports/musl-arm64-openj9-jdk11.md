---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:02:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 14-16 cores)</summary>

```
1789995347 14
1789995352 14
1789995357 14
1789995362 14
1789995367 14
1789995372 14
1789995377 14
1789995382 14
1789995387 14
1789995392 14
1789995397 14
1789995402 14
1789995407 14
1789995412 14
1789995417 16
1789995422 16
1789995427 16
1789995432 16
1789995437 14
1789995442 14
```
</details>

---

