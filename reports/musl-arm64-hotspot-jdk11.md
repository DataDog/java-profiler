---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-15 03:56:29 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 13 |
| Allocations | 175 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1792050776 54
1792050781 54
1792050786 54
1792050791 54
1792050796 54
1792050801 49
1792050806 49
1792050811 49
1792050816 49
1792050821 49
1792050826 49
1792050831 49
1792050836 49
1792050841 49
1792050846 49
1792050851 49
1792050856 49
1792050861 49
1792050866 49
1792050871 54
```
</details>

---

