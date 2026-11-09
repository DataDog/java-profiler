---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 15:05:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 26-36 cores)</summary>

```
1794254462 36
1794254467 36
1794254472 36
1794254477 36
1794254482 36
1794254487 36
1794254492 36
1794254497 36
1794254502 36
1794254507 36
1794254512 36
1794254517 31
1794254522 31
1794254527 31
1794254532 31
1794254537 26
1794254542 26
1794254547 26
1794254552 26
1794254557 26
```
</details>

---

