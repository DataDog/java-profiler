---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:28:42 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 11 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 33-36 cores)</summary>

```
1794392574 33
1794392579 33
1794392584 33
1794392589 33
1794392594 33
1794392599 33
1794392604 33
1794392609 33
1794392614 33
1794392619 33
1794392624 33
1794392629 33
1794392634 33
1794392639 33
1794392644 36
1794392649 36
1794392654 36
1794392659 36
1794392664 36
1794392669 36
```
</details>

---

