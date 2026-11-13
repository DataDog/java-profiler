---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 00:07:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1794546138 63
1794546143 63
1794546148 63
1794546153 63
1794546158 63
1794546163 63
1794546168 63
1794546173 63
1794546178 63
1794546183 63
1794546188 59
1794546193 59
1794546198 59
1794546203 59
1794546208 59
1794546213 59
1794546218 59
1794546223 61
1794546228 61
1794546233 61
```
</details>

---

