---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:01:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 11 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794326107 48
1794326112 48
1794326117 48
1794326122 48
1794326127 48
1794326132 48
1794326137 48
1794326142 48
1794326147 48
1794326152 48
1794326157 48
1794326162 48
1794326167 48
1794326172 48
1794326177 43
1794326182 43
1794326187 43
1794326192 43
1794326197 43
1794326202 43
```
</details>

---

