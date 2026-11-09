---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 10:19:58 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794237214 30
1794237219 30
1794237224 30
1794237229 30
1794237234 30
1794237239 30
1794237244 32
1794237249 32
1794237254 30
1794237259 30
1794237264 30
1794237269 30
1794237274 30
1794237279 30
1794237284 30
1794237289 30
1794237294 30
1794237299 30
1794237304 30
1794237309 30
```
</details>

---

