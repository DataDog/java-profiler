---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:44:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 27-33 cores)</summary>

```
1773394717 29
1773394722 29
1773394727 29
1773394732 29
1773394737 29
1773394742 29
1773394747 29
1773394752 29
1773394757 29
1773394762 29
1773394767 33
1773394772 33
1773394777 33
1773394782 27
1773394787 27
1773394792 27
1773394797 27
1773394802 32
1773394807 32
1773394812 32
```
</details>

---

