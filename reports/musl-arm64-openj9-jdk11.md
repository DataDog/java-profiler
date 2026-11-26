---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:21:28 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795706156 64
1795706161 64
1795706166 64
1795706171 64
1795706176 64
1795706181 64
1795706186 64
1795706191 64
1795706196 64
1795706201 64
1795706206 64
1795706211 64
1795706216 64
1795706221 64
1795706226 64
1795706231 64
1795706236 64
1795706241 64
1795706246 64
1795706251 64
```
</details>

---

