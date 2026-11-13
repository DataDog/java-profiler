---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 00:07:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 13 |
| Allocations | 85 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794546195 38
1794546200 38
1794546205 38
1794546210 38
1794546215 38
1794546220 38
1794546225 38
1794546230 38
1794546235 38
1794546240 38
1794546245 38
1794546250 43
1794546255 43
1794546260 43
1794546265 43
1794546270 43
1794546275 43
1794546280 43
1794546285 43
1794546290 43
```
</details>

---

