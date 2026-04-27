---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 16:33:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777321747 64
1777321752 64
1777321757 64
1777321762 64
1777321767 64
1777321772 64
1777321777 64
1777321782 64
1777321787 64
1777321792 64
1777321797 64
1777321802 64
1777321807 64
1777321812 64
1777321817 64
1777321822 64
1777321827 64
1777321832 64
1777321837 64
1777321842 64
```
</details>

---

