---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:59:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 72-78 cores)</summary>

```
1794588787 72
1794588792 72
1794588797 72
1794588802 72
1794588807 72
1794588812 72
1794588817 72
1794588822 72
1794588827 72
1794588832 72
1794588837 72
1794588842 78
1794588847 78
1794588852 78
1794588857 78
1794588862 78
1794588867 78
1794588872 78
1794588877 78
1794588882 78
```
</details>

---

