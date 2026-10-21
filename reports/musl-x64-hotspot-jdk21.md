---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 05:55:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1792576204 12
1792576209 12
1792576214 12
1792576219 12
1792576224 12
1792576229 12
1792576234 12
1792576239 12
1792576244 12
1792576249 12
1792576254 12
1792576259 12
1792576264 12
1792576269 10
1792576274 10
1792576279 10
1792576284 10
1792576289 10
1792576294 10
1792576299 10
```
</details>

---

