---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 00:53:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 12 |
| Allocations | 97 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792385343 46
1792385348 46
1792385353 46
1792385358 46
1792385363 46
1792385368 46
1792385373 46
1792385378 46
1792385383 46
1792385388 46
1792385393 46
1792385398 48
1792385403 48
1792385408 48
1792385413 48
1792385418 48
1792385423 48
1792385428 48
1792385433 48
1792385438 48
```
</details>

---

