---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-01 20:28:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 10 |
| Allocations | 418 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793582671 51
1793582676 51
1793582681 51
1793582686 51
1793582691 51
1793582696 51
1793582701 51
1793582706 51
1793582711 51
1793582716 51
1793582721 51
1793582726 51
1793582731 51
1793582736 51
1793582741 51
1793582746 51
1793582751 51
1793582756 51
1793582761 51
1793582766 51
```
</details>

---

