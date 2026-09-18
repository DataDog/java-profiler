---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:31:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 17-37 cores)</summary>

```
1789712757 17
1789712762 17
1789712767 17
1789712772 17
1789712777 17
1789712782 17
1789712787 17
1789712792 17
1789712797 17
1789712802 17
1789712807 17
1789712812 17
1789712817 17
1789712822 17
1789712827 17
1789712832 37
1789712837 37
1789712842 21
1789712847 21
1789712852 21
```
</details>

---

