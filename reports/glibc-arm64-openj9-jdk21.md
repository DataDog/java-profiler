---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-03 05:48:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 11 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1788428731 48
1788428736 48
1788428741 48
1788428746 48
1788428751 48
1788428756 48
1788428761 48
1788428766 48
1788428771 48
1788428776 48
1788428781 48
1788428786 48
1788428791 48
1788428796 48
1788428801 43
1788428806 43
1788428811 43
1788428816 43
1788428821 43
1788428826 43
```
</details>

---

