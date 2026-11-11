---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:47:15 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794408138 48
1794408143 48
1794408148 48
1794408153 48
1794408158 48
1794408163 48
1794408168 48
1794408173 48
1794408178 48
1794408183 43
1794408188 43
1794408193 43
1794408198 43
1794408203 43
1794408208 43
1794408213 43
1794408218 43
1794408223 43
1794408228 43
1794408233 43
```
</details>

---

