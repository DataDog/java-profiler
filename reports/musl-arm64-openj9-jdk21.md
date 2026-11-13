---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 16:21:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 14 |
| Allocations | 161 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794604666 48
1794604671 48
1794604676 48
1794604681 48
1794604686 48
1794604691 48
1794604697 48
1794604702 48
1794604707 48
1794604712 48
1794604717 48
1794604722 48
1794604727 48
1794604732 48
1794604737 43
1794604742 43
1794604747 43
1794604752 43
1794604757 43
1794604762 43
```
</details>

---

