---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-01 20:32:51 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793582747 48
1793582752 48
1793582757 48
1793582762 48
1793582767 48
1793582772 48
1793582777 48
1793582782 48
1793582787 48
1793582792 48
1793582797 48
1793582802 48
1793582807 48
1793582812 48
1793582817 48
1793582822 48
1793582827 48
1793582832 48
1793582837 48
1793582842 48
```
</details>

---

