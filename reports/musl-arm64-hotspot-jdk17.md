---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 07:11:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 40-43 cores)</summary>

```
1795694800 40
1795694805 40
1795694810 40
1795694816 42
1795694821 42
1795694826 42
1795694831 42
1795694836 42
1795694841 42
1795694846 42
1795694851 42
1795694856 42
1795694861 42
1795694866 42
1795694871 42
1795694876 42
1795694881 42
1795694886 41
1795694891 41
1795694896 41
```
</details>

---

