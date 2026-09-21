---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:02:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 62-72 cores)</summary>

```
1789995342 67
1789995347 67
1789995352 67
1789995357 67
1789995362 67
1789995367 67
1789995372 72
1789995377 72
1789995382 72
1789995387 72
1789995392 72
1789995397 72
1789995402 72
1789995407 72
1789995412 72
1789995417 72
1789995422 72
1789995427 72
1789995432 72
1789995437 72
```
</details>

---

