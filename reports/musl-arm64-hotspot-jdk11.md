---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 09:45:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 13 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (5 unique values: 27-43 cores)</summary>

```
1791466777 42
1791466782 42
1791466787 42
1791466792 42
1791466797 42
1791466802 42
1791466807 42
1791466812 43
1791466817 43
1791466822 43
1791466827 43
1791466832 43
1791466837 43
1791466842 41
1791466847 41
1791466852 41
1791466857 41
1791466862 41
1791466867 41
1791466872 41
```
</details>

---

