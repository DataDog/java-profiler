---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 12:37:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (3 unique values: 28-38 cores)</summary>

```
1794936753 33
1794936758 33
1794936763 33
1794936768 33
1794936773 33
1794936778 33
1794936783 33
1794936788 33
1794936793 33
1794936798 33
1794936803 33
1794936808 28
1794936813 28
1794936818 33
1794936823 33
1794936828 33
1794936833 33
1794936838 28
1794936843 28
1794936848 28
```
</details>

---

