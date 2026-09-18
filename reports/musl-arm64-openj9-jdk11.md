---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:32:47 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 932 |
| Sample Rate | 15.53/sec |
| Health Score | 971% |
| Threads | 8 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789712707 38
1789712712 38
1789712717 38
1789712722 43
1789712727 43
1789712732 48
1789712737 48
1789712742 48
1789712747 48
1789712752 48
1789712757 48
1789712762 48
1789712767 48
1789712772 48
1789712777 48
1789712782 48
1789712787 48
1789712792 48
1789712797 48
1789712802 48
```
</details>

---

