---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-01 20:32:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793582757 32
1793582762 32
1793582767 32
1793582772 32
1793582777 32
1793582782 32
1793582787 32
1793582792 32
1793582797 32
1793582802 32
1793582807 32
1793582812 32
1793582817 32
1793582822 32
1793582827 32
1793582832 32
1793582837 32
1793582842 32
1793582847 32
1793582852 32
```
</details>

---

