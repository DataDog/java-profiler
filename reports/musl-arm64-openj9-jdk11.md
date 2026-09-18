---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:07:47 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (4 unique values: 23-33 cores)</summary>

```
1789743556 24
1789743561 24
1789743566 24
1789743571 24
1789743576 24
1789743581 24
1789743586 24
1789743591 24
1789743596 24
1789743601 24
1789743606 24
1789743611 29
1789743616 29
1789743621 29
1789743626 29
1789743631 23
1789743636 23
1789743641 23
1789743646 23
1789743651 23
```
</details>

---

