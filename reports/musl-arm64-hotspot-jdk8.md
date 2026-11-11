---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-11 06:24:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 38-47 cores)</summary>

```
1794395941 45
1794395946 45
1794395951 44
1794395956 44
1794395961 47
1794395966 47
1794395971 47
1794395976 47
1794395981 47
1794395986 47
1794395991 47
1794395996 47
1794396001 43
1794396006 43
1794396011 43
1794396016 43
1794396021 43
1794396026 43
1794396031 43
1794396036 43
```
</details>

---

