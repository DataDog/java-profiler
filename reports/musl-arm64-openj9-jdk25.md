---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 05:04:27 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 13 |
| Allocations | 168 |

<details>
<summary>CPU Timeline (3 unique values: 25-43 cores)</summary>

```
1792400117 43
1792400122 43
1792400127 43
1792400132 43
1792400137 43
1792400142 43
1792400147 43
1792400153 43
1792400158 43
1792400163 43
1792400168 43
1792400173 43
1792400178 43
1792400183 43
1792400188 43
1792400193 43
1792400198 43
1792400203 30
1792400208 30
1792400213 30
```
</details>

---

