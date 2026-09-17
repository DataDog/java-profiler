---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 19:14:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 10 |
| Allocations | 188 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1789686521 43
1789686526 43
1789686531 43
1789686537 43
1789686542 43
1789686547 38
1789686552 38
1789686557 38
1789686562 38
1789686567 38
1789686572 38
1789686577 38
1789686582 38
1789686587 38
1789686592 38
1789686597 38
1789686602 38
1789686607 38
1789686612 38
1789686617 38
```
</details>

---

