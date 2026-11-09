---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 10:36:32 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 39-44 cores)</summary>

```
1794238194 42
1794238199 42
1794238204 42
1794238209 42
1794238214 44
1794238219 44
1794238224 39
1794238229 39
1794238234 39
1794238239 39
1794238244 39
1794238249 39
1794238254 39
1794238259 39
1794238264 39
1794238269 39
1794238274 39
1794238279 39
1794238284 44
1794238289 44
```
</details>

---

