---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 01:30:58 EDT

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
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776662747 64
1776662752 64
1776662757 64
1776662762 64
1776662767 64
1776662772 64
1776662777 64
1776662782 64
1776662787 64
1776662792 64
1776662797 64
1776662802 64
1776662807 64
1776662812 64
1776662817 64
1776662822 64
1776662827 64
1776662832 64
1776662837 64
1776662842 64
```
</details>

---

