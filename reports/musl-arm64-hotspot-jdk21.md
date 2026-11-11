---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 15:02:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 44-51 cores)</summary>

```
1794427067 46
1794427072 46
1794427077 46
1794427082 46
1794427087 46
1794427092 46
1794427097 46
1794427102 46
1794427107 46
1794427112 46
1794427117 46
1794427122 46
1794427127 44
1794427132 44
1794427137 44
1794427142 44
1794427147 44
1794427152 44
1794427157 44
1794427162 44
```
</details>

---

