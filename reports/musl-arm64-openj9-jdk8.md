---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-24 05:51:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795517178 48
1795517183 48
1795517188 48
1795517193 48
1795517198 48
1795517203 48
1795517208 48
1795517213 48
1795517218 48
1795517223 48
1795517228 48
1795517233 48
1795517238 48
1795517243 48
1795517248 48
1795517253 48
1795517258 64
1795517263 64
1795517268 64
1795517273 64
```
</details>

---

