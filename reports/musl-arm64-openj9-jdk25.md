---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:55:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 42 |
| Sample Rate | 0.70/sec |
| Health Score | 44% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794484067 32
1794484072 32
1794484077 32
1794484082 32
1794484087 32
1794484092 32
1794484097 32
1794484102 32
1794484107 32
1794484112 32
1794484117 32
1794484122 32
1794484127 32
1794484132 32
1794484137 32
1794484142 32
1794484147 32
1794484152 32
1794484157 32
1794484162 32
```
</details>

---

