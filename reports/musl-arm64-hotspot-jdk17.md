---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 12:43:59 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 13 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (6 unique values: 32-43 cores)</summary>

```
1793291821 34
1793291826 34
1793291831 34
1793291836 34
1793291841 34
1793291846 32
1793291851 32
1793291856 32
1793291861 32
1793291866 32
1793291871 32
1793291876 32
1793291881 33
1793291886 33
1793291891 39
1793291896 39
1793291901 39
1793291906 39
1793291911 41
1793291916 41
```
</details>

---

