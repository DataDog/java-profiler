---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 10:07:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 12 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 61-73 cores)</summary>

```
1770130856 63
1770130861 63
1770130866 63
1770130871 63
1770130876 63
1770130881 63
1770130886 63
1770130891 61
1770130896 61
1770130901 61
1770130906 61
1770130911 61
1770130916 61
1770130921 61
1770130926 61
1770130931 61
1770130936 61
1770130941 73
1770130946 73
1770130951 73
```
</details>

---

