---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:47:41 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1104 |
| Sample Rate | 18.40/sec |
| Health Score | 1150% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1790091738 31
1790091743 31
1790091748 31
1790091753 31
1790091758 31
1790091763 31
1790091768 31
1790091773 31
1790091778 31
1790091783 31
1790091788 31
1790091793 31
1790091798 31
1790091803 31
1790091808 31
1790091813 31
1790091818 31
1790091823 31
1790091828 36
1790091833 36
```
</details>

---

