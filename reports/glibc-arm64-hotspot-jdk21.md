---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-26 14:48:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 62-63 cores)</summary>

```
1787769774 62
1787769779 62
1787769784 62
1787769789 62
1787769794 62
1787769799 62
1787769804 62
1787769809 62
1787769814 63
1787769819 63
1787769824 63
1787769829 63
1787769834 63
1787769839 63
1787769844 63
1787769849 62
1787769854 62
1787769859 62
1787769864 62
1787769869 62
```
</details>

---

