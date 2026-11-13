---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 00:07:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 7 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794546195 31
1794546200 31
1794546205 31
1794546210 31
1794546215 31
1794546220 31
1794546225 31
1794546230 31
1794546235 31
1794546240 31
1794546245 31
1794546250 31
1794546255 31
1794546260 31
1794546265 31
1794546270 31
1794546275 31
1794546280 31
1794546285 36
1794546290 36
```
</details>

---

