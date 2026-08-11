---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 04:47:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1786437751 64
1786437756 64
1786437761 64
1786437766 64
1786437771 64
1786437776 64
1786437781 64
1786437786 64
1786437791 64
1786437796 64
1786437801 56
1786437806 56
1786437811 56
1786437816 56
1786437821 56
1786437826 56
1786437831 56
1786437836 56
1786437841 56
1786437846 56
```
</details>

---

