---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 16:05:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1793739722 31
1793739727 31
1793739732 31
1793739737 31
1793739742 31
1793739747 31
1793739752 31
1793739757 31
1793739762 31
1793739767 31
1793739772 31
1793739777 31
1793739782 31
1793739787 31
1793739792 31
1793739797 31
1793739802 31
1793739807 31
1793739812 31
1793739817 31
```
</details>

---

