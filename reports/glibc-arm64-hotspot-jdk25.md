---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:47:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 41 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790091723 50
1790091728 50
1790091733 50
1790091738 50
1790091743 50
1790091748 50
1790091753 50
1790091758 50
1790091763 50
1790091768 50
1790091773 50
1790091778 50
1790091783 50
1790091788 50
1790091793 50
1790091798 50
1790091803 50
1790091808 50
1790091813 50
1790091818 50
```
</details>

---

