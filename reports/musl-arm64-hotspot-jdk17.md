---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 09:45:20 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 11 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 40-44 cores)</summary>

```
1791466762 40
1791466767 40
1791466772 40
1791466777 40
1791466782 40
1791466787 40
1791466792 40
1791466797 40
1791466802 40
1791466807 40
1791466812 40
1791466817 40
1791466822 40
1791466827 40
1791466832 40
1791466837 40
1791466842 40
1791466847 40
1791466852 40
1791466857 40
```
</details>

---

