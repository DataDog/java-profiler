---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 17:43:40 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 11 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1790026688 33
1790026693 33
1790026698 33
1790026703 33
1790026708 33
1790026714 38
1790026719 38
1790026724 38
1790026729 38
1790026734 38
1790026739 38
1790026744 43
1790026749 43
1790026754 43
1790026759 43
1790026764 43
1790026769 43
1790026774 48
1790026779 48
1790026784 48
```
</details>

---

