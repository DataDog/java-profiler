---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 00:07:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 63-70 cores)</summary>

```
1794546164 65
1794546169 65
1794546174 65
1794546179 65
1794546184 63
1794546189 63
1794546195 63
1794546200 68
1794546205 68
1794546210 68
1794546215 68
1794546220 70
1794546225 70
1794546230 70
1794546235 70
1794546240 70
1794546245 70
1794546250 70
1794546255 70
1794546260 70
```
</details>

---

