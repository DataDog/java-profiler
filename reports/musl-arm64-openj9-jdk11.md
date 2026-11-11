---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 07:51:58 EST

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 16-18 cores)</summary>

```
1794401162 18
1794401167 18
1794401172 18
1794401177 18
1794401182 18
1794401187 18
1794401192 18
1794401197 17
1794401202 17
1794401207 17
1794401212 17
1794401217 17
1794401222 17
1794401227 17
1794401232 17
1794401237 17
1794401242 17
1794401247 17
1794401252 17
1794401257 18
```
</details>

---

