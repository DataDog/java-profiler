---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-24 09:28:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1787577816 32
1787577821 32
1787577826 32
1787577831 32
1787577836 32
1787577841 32
1787577846 32
1787577851 32
1787577856 32
1787577861 32
1787577866 32
1787577871 32
1787577876 32
1787577881 32
1787577886 32
1787577891 32
1787577896 32
1787577901 32
1787577906 32
1787577911 32
```
</details>

---

