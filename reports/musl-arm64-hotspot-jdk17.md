---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 12:37:06 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (4 unique values: 31-51 cores)</summary>

```
1794936772 33
1794936777 33
1794936782 33
1794936787 33
1794936792 46
1794936797 46
1794936802 51
1794936807 51
1794936812 51
1794936817 51
1794936822 51
1794936827 51
1794936832 51
1794936837 51
1794936842 51
1794936847 51
1794936852 51
1794936857 51
1794936863 51
1794936868 51
```
</details>

---

