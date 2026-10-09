---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 03:28:09 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 15 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1791530698 32
1791530703 32
1791530708 32
1791530713 27
1791530718 27
1791530723 27
1791530728 27
1791530733 27
1791530738 27
1791530743 27
1791530748 27
1791530753 27
1791530758 27
1791530763 27
1791530768 27
1791530773 27
1791530778 27
1791530783 27
1791530788 27
1791530793 27
```
</details>

---

