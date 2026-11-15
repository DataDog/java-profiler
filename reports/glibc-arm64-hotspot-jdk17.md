---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 08:56:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1794750701 31
1794750706 31
1794750711 31
1794750716 31
1794750721 31
1794750726 31
1794750731 32
1794750736 32
1794750741 32
1794750746 32
1794750751 32
1794750756 32
1794750761 32
1794750766 32
1794750771 32
1794750776 32
1794750781 32
1794750786 32
1794750791 32
1794750796 32
```
</details>

---

