---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 12:41:38 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 12 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 34-46 cores)</summary>

```
1794332024 39
1794332029 39
1794332034 34
1794332039 34
1794332044 46
1794332049 46
1794332054 34
1794332059 34
1794332064 34
1794332069 34
1794332074 34
1794332079 34
1794332084 34
1794332089 34
1794332094 34
1794332099 34
1794332104 34
1794332109 34
1794332114 34
1794332119 39
```
</details>

---

