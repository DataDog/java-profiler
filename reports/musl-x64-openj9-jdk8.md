---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-18 08:24:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787055567 96
1787055572 96
1787055577 96
1787055582 96
1787055587 96
1787055592 96
1787055597 88
1787055602 88
1787055607 88
1787055612 88
1787055617 88
1787055622 88
1787055627 88
1787055632 88
1787055637 88
1787055642 88
1787055647 88
1787055652 88
1787055657 88
1787055662 88
```
</details>

---

