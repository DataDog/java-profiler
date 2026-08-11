---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 09:44:06 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 14 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 10-11 cores)</summary>

```
1786455565 10
1786455570 10
1786455575 10
1786455580 10
1786455585 10
1786455590 10
1786455595 10
1786455600 10
1786455606 10
1786455611 10
1786455616 11
1786455621 11
1786455626 11
1786455631 11
1786455636 11
1786455641 11
1786455646 11
1786455651 11
1786455656 11
1786455661 11
```
</details>

---

