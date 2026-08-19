---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 13:04:19 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1787158809 34
1787158814 34
1787158819 34
1787158824 34
1787158829 34
1787158834 34
1787158839 32
1787158844 32
1787158849 32
1787158855 32
1787158860 32
1787158865 32
1787158870 32
1787158875 32
1787158880 32
1787158885 32
1787158890 32
1787158895 32
1787158900 32
1787158905 32
```
</details>

---

