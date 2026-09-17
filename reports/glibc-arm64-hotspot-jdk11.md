---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 19:15:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1789686692 40
1789686697 40
1789686702 40
1789686707 40
1789686712 40
1789686717 40
1789686722 40
1789686727 40
1789686732 40
1789686737 40
1789686742 40
1789686747 40
1789686752 40
1789686757 40
1789686762 40
1789686767 40
1789686772 40
1789686777 40
1789686782 40
1789686787 40
```
</details>

---

