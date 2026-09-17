---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 10:30:06 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 14 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1789655029 43
1789655034 43
1789655039 43
1789655044 43
1789655049 43
1789655054 43
1789655059 43
1789655064 43
1789655069 43
1789655074 43
1789655079 43
1789655084 43
1789655089 43
1789655094 43
1789655099 43
1789655104 43
1789655109 43
1789655114 43
1789655119 38
1789655124 38
```
</details>

---

