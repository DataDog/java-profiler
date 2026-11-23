---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 39-59 cores)</summary>

```
1795434730 39
1795434735 39
1795434740 59
1795434745 59
1795434750 59
1795434755 59
1795434761 59
1795434766 59
1795434771 57
1795434776 57
1795434781 57
1795434786 57
1795434791 57
1795434796 57
1795434801 57
1795434806 57
1795434811 57
1795434816 57
1795434821 57
1795434826 57
```
</details>

---

