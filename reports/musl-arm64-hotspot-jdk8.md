---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790172192 48
1790172197 48
1790172202 48
1790172207 48
1790172212 48
1790172217 48
1790172222 48
1790172227 48
1790172232 48
1790172237 48
1790172243 48
1790172248 48
1790172253 48
1790172258 48
1790172263 48
1790172268 46
1790172273 46
1790172278 46
1790172283 46
1790172288 46
```
</details>

---

